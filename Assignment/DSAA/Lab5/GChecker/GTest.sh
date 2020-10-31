while true; do
    ./GGen
    time ./GOld<in.io>old.out
    time ./GNew<in.io>new.out
    if diff old.out new.out; then
        printf "AC\n"
    else
        echo "WA\n"
        exit 0
    fi
done