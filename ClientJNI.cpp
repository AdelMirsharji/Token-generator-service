#include<iostream>
#include<jni.h>
#include "ClientJNI.h"
void sayHello(){
  std::cout << "Hello from C++ !!" << std::endl;
}
JNIEXPORT void JNICALL Java_ClientJNI_sayHello
  (JNIEnv* env, jobject thisObject) {
    sayHello();
}