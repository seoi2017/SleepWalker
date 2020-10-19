while true; do
    ./FGen
    time ./FOld<in.io>old.out
    time ./FNew<in.io>new.out
    if diff old.out new.out; then
        printf "AC\n"
    else
        echo "WA\n"
        exit 0
    fi
done