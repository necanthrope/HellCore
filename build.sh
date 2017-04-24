#!/bin/sh

# Run through the (standard) build steps.
# This is mainly to simplify things for the user, who may not be familiar with
# the standard Linux configure/make steps.


# If any of the commands fail, just die.
set -e


# Make sure we're actually in the project directory.
cd "$(dirname "$0")"


# The build stages.

generate_project() {
  # Generate the build system, configure, and build the project.

  # Make sure we've got autoconf installed.
  if ! autoreconf --version >/dev/null 2>&1
  then
    echo "I couldn't find autoreconf."
    echo "This probably means you don't have autoconf or automake installed."
    echo "Please install all the dependencies in README.md."
    exit 1
  fi

  echo "Regenerating the project build system..."
  ./autogen.sh

  configure_project
}

configure_project() {
  # Configure and build the project.

  echo "Configuring the project..."
  ./configure

  build_project
}

build_project() {
  # Build the project with make.

  # Make sure we've got make installed.
  if ! make --version >/dev/null 2>&1
  then
    echo "I couldn't find make."
    echo "This probably means you don't have make installed."
    echo "Please install all the dependencies in README.md."
    exit 1
  fi

  echo "Building the project..."
  make
}


# Determine what stage to start at, depending on what part of the build system
# has been generated.

if [ -e Makefile ]
then

  # Our build system's already ready.
  # Just build it.
  build_project

elif [ -e configure ]
then

  # Our build system's created, but needs to be configured before building.
  configure_project

elif [ -e configure.ac ]
then

  # We need to regenerate the build system before building it.
  generate_project

else

  # None of the build system files exist.

  echo "ERROR: Cannot find the build system files."
  echo "Do you have a clean and uncorrupted source tree?"

  exit 2

fi
