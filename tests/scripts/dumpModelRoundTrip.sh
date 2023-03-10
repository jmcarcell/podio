#!/usr/bin/env bash
# Script to check that an EDM definition dumped from a file is "equivalent" to
# the original definition. Essentially does not check that the YAML file is the
# same, but rather that the generated code is the same

set -e

EXCLUDE_SIO=${1}  # SIO excluded or not
INPUT_FILE=${2}  # the datafile
EDM_NAME=${3}  # the name of the EDM
COMP_BASE_FOLDER=""  # where the source to compare against is
if [ -$# -gt 3 ]; then
    COMP_BASE_FOLDER=${4}
fi

# Create a few temporary but unique files and directories to store output
DUMPED_MODEL=${INPUT_FILE}.dumped_${EDM_NAME}.yaml
OUTPUT_FOLDER=${INPUT_FILE}.dumped_${EDM_NAME}
mkdir -p ${OUTPUT_FOLDER}

# Dump the model to a yaml file
${PODIO_BASE}/tools/podio-dump --dump-edm ${EDM_NAME} ${INPUT_FILE} > ${DUMPED_MODEL}

# Regenerate the code via the class generator and the freshly dumped model
${PODIO_BASE}/python/podio_class_generator.py \
    --clangformat \
    ${DUMPED_MODEL} \
    ${OUTPUT_FOLDER} \
    ${EDM_NAME} \
    ${IO_HANDLERS}

# Compare to the originally generated code, that has been used to write the data
# file. Need to diff subfolders explitly here because $PODIO_BASE/tests contains
# more stuff
if [ ${EXCLUDE_SIO} = "true" ]; then
diff -ru ${OUTPUT_FOLDER}/${EDM_NAME} ${PODIO_BASE}/tests/${COMP_BASE_FOLDER}/${EDM_NAME} --exclude='*SIO*'
diff -ru ${OUTPUT_FOLDER}/src ${PODIO_BASE}/tests/${COMP_BASE_FOLDER}/src --exclude='*SIO*'
else
diff -ru ${OUTPUT_FOLDER}/${EDM_NAME} ${PODIO_BASE}/tests/${COMP_BASE_FOLDER}/${EDM_NAME} 
diff -ru ${OUTPUT_FOLDER}/src ${PODIO_BASE}/tests/${COMP_BASE_FOLDER}/src
fi
diff -u ${OUTPUT_FOLDER}/podio_generated_files.cmake ${PODIO_BASE}/tests/podio_generated_files.cmake
