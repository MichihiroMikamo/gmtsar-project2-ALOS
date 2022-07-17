イメージを作る
docker build -t gmtsar-image0.1 .

一つ上のフォルダに移動してコンテナを作る
docker run --name gmtsar-container20220707 -it --gpus all --shm-size=2gb -v $(pwd):/home -it gmtsar-image0.1 /bin/bash

