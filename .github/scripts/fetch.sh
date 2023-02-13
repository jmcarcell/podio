deps=$(spack dependents $1)
deps="edm4hep k4fwcore"
for d in $deps
do
    echo $d
done
ls -lah
