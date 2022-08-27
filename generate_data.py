import argparse
import random

INT_MAX = 2 ** 31 - 1
verbose = False
file = None

def add_log(message):
    if verbose:
        file.write(f"{message}\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--file", "-f", type=str, default="inputs/io-test.txt", help="Output file"
    )
    parser.add_argument("--max-size", "-m", type=int, default=7853, help="Max table size (M)")
    parser.add_argument("--max-n", "-n", type=int, default=INT_MAX, help="Max N")
    parser.add_argument(
        "--insert-ops",
        "-i",
        type=int,
        default=1000,
        help="Number of Insert operations per cycle",
    )
    parser.add_argument(
        "--remove-ops",
        "-r",
        type=int,
        default=1000,
        help="Number of Remove operations per cycle",
    )
    parser.add_argument(
        "--cycles",
        "-c",
        type=int,
        default=100,
        help="Number of Insert/Remove cycles",
    )
    parser.add_argument(
        "--description", "-d", type=str, default="Test data", help="Description of the test"
    )
    parser.add_argument(
        "--verbose",
        "-v",
        action="store_true",
        help="Add print operations to stdout",
    )
    parser.add_argument("--log-every", "-l", type=int, default=10, help="Log every l operations")
    parser.add_argument("--seed", "-s", type=int, default=42, help="Random Seed")
    args = parser.parse_args()

    assert args.insert_ops <= args.max_n
    assert args.remove_ops <= args.insert_ops

    # prepare structures
    random.seed(args.seed)
    verbose = args.verbose
    file = open(args.file, "w")
    # add headers
    add_log(f"# {args.description}")
    add_log(f"# Using seed {args.seed}")
    file.write(f"m {args.max_size}\n")

    # generate data
    ops = 0
    for _ in range(args.cycles):
        hashmap_state = []
        insert_pool = list(range(args.max_n))

        # generate insertions
        add_log(f"# Inserting {args.insert_ops}")
        random.shuffle(insert_pool)
        for i in range(args.insert_ops):
            n = insert_pool.pop(0)
            file.write(f"insert {n} {random.randint(0, INT_MAX)}\n")
            hashmap_state.append(n)

            ops += 1
            if ops % args.log_every == 0:
                file.write(f"stats\n")

        if ops % args.log_every == 0:
            file.write(f"stats\n")

        # generate removals
        add_log(f"# Removing {args.remove_ops}")
        random.shuffle(hashmap_state)
        for i in range(args.remove_ops):
            n = hashmap_state.pop(0)
            file.write(f"remove {n}\n")

            ops += 1
            if ops % args.log_every == 0:
                file.write(f"stats\n")

    file.close()
    print("Done")
