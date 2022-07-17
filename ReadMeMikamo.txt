コンテナを作る
docker run --name gmtsar-container20220709 -it --gpus all --shm-size=2gb -v $(pwd):/home -it gmtsar-image0.1 /bin/bash
