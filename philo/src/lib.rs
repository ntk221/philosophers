use std::time::{SystemTime, Duration};
use std::thread;

fn get_time() -> u64 {
    SystemTime::now()
        .duration_since(SystemTime::UNIX_EPOCH)
        .expect("Failed to get time")
        .as_millis() as u64
}

fn msleep(t: u64) {
    let end = get_time() + t;

    while get_time() < end {
        thread::sleep(Duration::from_millis(100));
    }
}
