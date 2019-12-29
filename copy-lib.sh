set -eux

./gradlew clean assembleDebug

cp \
  app/build/intermediates/stripped_native_libs/debug/out/lib/armeabi-v7a/libbreakpad-client.so \
  ../telpo-service/app/src/main/libs/armeabi/libbreakpad-client.so
