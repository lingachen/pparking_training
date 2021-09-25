#pragma once

void init_threads();
TASK_FUNC panel_task(void *data);
TASK_FUNC xfer_task(void *);
TASK_FUNC send_panel_task(void *data);