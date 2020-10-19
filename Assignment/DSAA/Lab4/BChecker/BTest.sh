while true; do
    ./BGen
    time ./BOld<in.io>old.out
    time ./BNew<in.io>new.out
    if diff old.out new.out; then
        printf "AC\n"
    else
        echo "WA\n"
        exit 0
    fi
done