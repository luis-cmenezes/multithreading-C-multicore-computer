#!/bin/bash
terminator -e "./shell-scripts/background_load_automation.sh"
sync; sync; sync;
./shell-scripts/quad_thread_automation.sh
sync; sync; sync;
./shell-scripts/double_thread_automation.sh
sync; sync; sync;
./shell-scripts/single_thread_automation.sh
sync; sync; sync;