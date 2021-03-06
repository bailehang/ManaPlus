#!/bin/bash

echo docker login registry.gitlab.com
docker login registry.gitlab.com

export IMAGE="registry.gitlab.com/manaplus/mxe:gcc6_shared_${BITS}"
export COMMAND="./tools/ci/jobs/mxe_gcc6_tests.sh --without-manaplusgame --without-dyecmd"
export PACKAGES="bash"
./tools/ci/scripts/docker_run_cross.sh || exit 1
mkdir dlls || true
export COMMAND="./tools/ci/scripts/copymxedlls.sh dlls"
ls -la dlls
echo copy dlls from docker
./tools/ci/scripts/docker_run_cross.sh || exit 1
