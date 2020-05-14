# podio

## Bug tracker
Please submit feature requests and bugs to
[https://sft.its.cern.ch/jira/projects/PODIO](https://sft.its.cern.ch/jira/projects/PODIO)

## Documentation

 - [Introduction](./doc/doc.md)
 - [Design](./doc/design.md)
 - [Data Model Syntax](./doc/datamodel_syntax.md)
 - [Examples](./doc/examples.md)
 - [Advanced Topics](./doc/advanced_topics.md)
 - [Contributing](./doc/contributing.md)

<!-- Browse the API documentation created with Doxygen at -->

<!-- [http://fccsw.web.cern.ch/fccsw/podio/index.html](http://fccsw.web.cern.ch/fccsw/podio/index.html). -->

## Prerequisites

If you are on lxplus, all the necessary software is preinstalled if you
use a recent LCG or FCC stack release.

On Mac OS or Ubuntu, you need to install the following software.

### ROOT 6.08.06

Install ROOT 6.08.06 (or later) and set up your ROOT environment:

    source <root_path>/bin/thisroot.sh

### Python > 2.7

Podio works with both python 2 and python3. Check your python version by doing:

    python --version

Check that the yaml python module is available

    python
    >>> import yaml

If the import goes fine (no message), you're all set. If not, you need to install yaml. For that, you need to:

1- install the C++ yaml library, which is used by the python module. On Mac OS, The easiest way to do that is to use homebrew (install homebrew if you don't have it yet):

    brew install libyaml

2- install the python yaml module (first install pip if you don't have it yet)

    pip install pyyaml

Check that you can now import the yaml module in python.


## Preparing the environment

Full use of PODIO requires you to set the `PODIO` environment variable
and modify `LD_LIBRARY_PATH` and `PYTHONPATH`. Some convenience scripts
are provided:

    # Set PODIO install area to `./install` and setup environment accordingly
    source ./init.sh

or

    # Setup environment based on current value of `PODIO`
    source ./env.sh

Or you can setup the environment entirely under your control: see `init.sh`
and `env.sh`.

## Compiling

If you are using the easy setup from `init.sh` then create separate build
and install areas, and trigger the build:

    mkdir build
    mkdir install
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ..
    make -j 4 install

To see a list of options, do this in the build-directory:

    cmake -LH ..

## Running

The examples are for creating a file "example.root",

    tests/write

and reading it again in C++,

    tests/read

It is also possible to read the file again using the
[`tests/read.py`](tests/read.py) script. Make sure to have run `init.sh`
and `env.sh` first. Additionally you have to make `ROOT` aware of
`libTestDataModel.so` to be able to read in the data types defined there. There
are two ways to do that. First it is possible to add the directory to the
`LD_LIBRARY_PATH`

    export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(pwd)/tests

Secondly it is also possible to explicitly load the library via `ROOT` in the
script by adding the following lines *after* the imports from `__future__`

```python
import os
BUILD_PATH = os.getcwd()

import ROOT
ROOT.gSystem.Load(os.path.join(BUILD_PATH, 'tests/libTestDataModel.so'))
```

Either of the two versions allows you to now read the `example.root` file again
using

     python ../tests/read.py

## Installing using SPACK

A recipe for building podio is included with the [spack package manager](https://github.com/spack/spack/blob/develop/var/spack/repos/builtin/packages/podio/package.py), so podio can also installed with:

```
spack install podio
```

Note that if you do not have any previous installations or registered system packages, this will compile ROOT and all its dependencies, which may be time-consuming.

## Modifying the data model

Podio features an example event data model, fully described in the yaml file
[tests/datalayout.yaml](tests/datalayout.yaml).
The C++ in [tests/datamodel/](tests/datamodel/) has been fully generated by a code generation script, [python/podio_class_generator.py](python/podio_class_generator.py).

To run the code generation script, do

    mkdir ../Tmp
    mkdir ../Tmp/data
    mkdir ../Tmp/src
    python ../python/podio_class_generator.py ../examples/datalayout.yaml ../Tmp data

The generation script has the following additional options:

- `--clangformat` (`-c`): Apply clang-format after file creation (uses [option `-style=file`](https://clang.llvm.org/docs/ClangFormatStyleOptions.html) with llvm as backup style), needs clang-format in `$PATH`.
- `--quiet` (`-q`): Suppress all print out to STDOUT
- `--dryrun` (`-d`): Only run the generation logic and validate yaml, do not write files to disk

## Running tests
After compilation you can run rudimentary tests with

    make test
