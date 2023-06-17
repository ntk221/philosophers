use std::sync::{Arc, Mutex};
use std::thread;

#[derive(Debug)]
struct Data {
    philo_num: usize,
    time_to_die: i32,
    time_to_eat: i32,
    time_to_sleep: i32,
}

#[derive(Clone, Debug)]
struct Philo {
    id: usize,
    left_fork: Arc<Mutex<()>>,
    right_fork: Arc<Mutex<()>>,
}

impl Philo {
    fn new(id: usize, left_fork: Arc<Mutex<()>>, right_fork: Arc<Mutex<()>>) -> Philo {
        Philo {
            id,
            left_fork,
            right_fork,
        }
    }

    fn eat(&self) {
        println!("Philosopher {} takes a seat", self.id);
        // TODO: 食事のロジック
    }

    fn think(&self) {
        // TODO: 思考のロジック
    }

    fn sleep(&self) {
        // TODO: スリープのロジック
    }

    fn dine(&self) {
        while !self.is_done() {
            self.eat();
            self.sleep();
            self.think();
        }
    }

    fn is_done(&self) -> bool {
        // TODO: 終了条件の判定ロジック
        false
    }
}

fn get_data(data: &mut Data, argv: &Vec<String>) -> bool {
    if argv.len() < 5 {
        return false;
    }

    if let Ok(philo_num) = argv[1].parse::<usize>() {
        data.philo_num = philo_num;
    } else {
        return false;
    }

    if let Ok(time_to_die) = argv[2].parse::<i32>() {
        data.time_to_die = time_to_die;
    } else {
        return false;
    }

    if let Ok(time_to_eat) = argv[3].parse::<i32>() {
        data.time_to_eat = time_to_eat;
    } else {
        return false;
    }

    if let Ok(time_to_sleep) = argv[4].parse::<i32>() {
        data.time_to_sleep = time_to_sleep;
    } else {
        return false;
    }

    true
}

fn main() {
    let mut data: Data = Data {
        philo_num: (0),
        time_to_die: (0),
        time_to_eat: (0),
        time_to_sleep: (0),
    };

    let args: Vec<String> = std::env::args().collect();

    let ret = get_data(&mut data, &args);

    assert_eq!(ret, true);

    println!("{:?}", data);

    let forks: Vec<_> = (0..data.philo_num)
        .map(|_| Arc::new(Mutex::new(())))
        .collect();

    let philosophers: Vec<_> = (0..data.philo_num)
        .map(|i: usize| {
            let left_fork = forks[i].clone();
            let right_fork = forks[(i + 1) % data.philo_num].clone();
            Philo::new(i + 1, left_fork, right_fork)
        })
        .collect();

    println!("{:?}", forks);
    println!("{:?}", philosophers);

    for philo in &philosophers {
        let philo = philo.clone();
        thread::spawn(move || {
            philo.dine();
        });
    }
}
