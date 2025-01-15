# linux build
git clone https://github.com/zitzitz/entt-archers-demo.git

cd entt-archers-demo

git submodule update --init

mkdir build

cd build

cmake ..

./archers

# Windows build
git clone https://github.com/zitzitz/entt-archers-demo.git

cd entt-archers-demo

git submodule update --init thirdparty/entt

Открыть в Visual Studio vsproj\vsproj.sln