#!/bin/sh

# This file is now a compatibility wrapper around the src/restart script.
# Any changes should be made there instead.

exec "$(dirname "$0")/restart" "$@"
