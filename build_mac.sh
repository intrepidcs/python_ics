#!/bin/sh

python_directory="/Library/Frameworks/Python.framework/Versions"
python_versions=("3.7" "3.8" "3.9" "3.10" "3.11")

# libusb dependencies
brew install automake libtool cmake clang-format
ret_value=$?
if [ $ret_value -ne 0 ]; then
    echo "Failed to install automake/libtoolgit..."
    exit $ret_value
fi

# Stash any changes we don't have committed.
git stash
ret_value=$?
if [ $ret_value -ne 0 ]; then
    echo "Failed to stash changes through git..."
    exit $ret_value
fi

# Make sure all the python versions are installed
for version in "${python_versions[@]}"
do
    python_exec="${python_directory}/${version}/bin/python3"
    # echo $python_exec
    $python_exec --version
    echo "Installing python dependencies..."
    $python_exec -m pip install wheel
    ret_value=$?
    if [ $ret_value -ne 0 ]; then
        echo "Python requirements for ${version} failed!"
        exit $ret_value
    fi
    echo "Building python ${version}..."
    $python_exec setup.py bdist_wheel --universal
    ret_value=$?
    if [ $ret_value -ne 0 ]; then
        echo "Builing python_ics module with Python ${version} failed!"
        exit $ret_value
    fi
done
