while true; do
    ./DGen
    time ./DOld<in.io>old.out
    time ./DNew<in.io>new.out
    if diff old.out new.out; then
        printf "AC\n"
    else
        echo "WA\n"
        exit 0
    fi
done