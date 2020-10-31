while true; do
    ./HGen
    time ./HOld<in.io>old.out
    time ./HNew<in.io>new.out
    if diff old.out new.out; then
        printf "AC\n"
    else
        echo "WA\n"
        exit 0
    fi
done