#if defined(__linux__)
    #include "/home/codeleaded/System/Static/Library/CStr.h"
    #include "/home/codeleaded/System/Static/Library/Pointer.h"
#elif defined(_WINE)
    #include "/home/codeleaded/System/Static/Library/CStr.h"
    #include "/home/codeleaded/System/Static/Library/Pointer.h"
#elif defined(_WIN32)
    #include "F:/home/codeleaded/System/Static/Library/CStr.h"
    #include "F:/home/codeleaded/System/Static/Library/Pointer.h"
#elif defined(__APPLE__)
    #error "Apple not supported!"
#else
    #error "Platform not supported!"
#endif

typedef struct Human {
    char* name;
    int iq;
    float height;
} Human;

Human Human_New(CStr name,int iq,float height){
    Human h;
    h.name = CStr_Cpy(name);
    h.iq = iq;
    h.height = height;
    return h;
}
void Human_Free(Human* p){
    CStr_Free(&p->name);
}
void Human_Print(Human* p){
    printf(" (%s %d %f) ",p->name,p->iq,p->height);
}

int main(int argc,char **argv){
    Pointer p = Pointer_New(3U,(unsigned int[]){ 2U,2U,2U },sizeof(Human),(void(*)(void*))Human_Free,(void(*)(void*))Human_Print);

    Pointer_Set(&p,(unsigned int[]){ 0U,0U,0U },(Human[]){ Human_New("Alice",120,5.5f) });
    Pointer_Set(&p,(unsigned int[]){ 0U,0U,1U },(Human[]){ Human_New("Steve",110,5.5f) });
    Pointer_Set(&p,(unsigned int[]){ 0U,1U,0U },(Human[]){ Human_New("Bob",140,5.5f) });
    Pointer_Set(&p,(unsigned int[]){ 0U,1U,1U },(Human[]){ Human_New("Bob",160,5.5f) });
    Pointer_Set(&p,(unsigned int[]){ 1U,0U,0U },(Human[]){ Human_New("Bob",110,5.5f) });
    Pointer_Set(&p,(unsigned int[]){ 1U,0U,1U },(Human[]){ Human_New("Bob",123,5.5f) });
    Pointer_Set(&p,(unsigned int[]){ 1U,1U,0U },(Human[]){ Human_New("Bob",189,5.5f) });
    Pointer_Set(&p,(unsigned int[]){ 1U,1U,1U },(Human[]){ Human_New("Bob",169,5.5f) });
    
    Pointer_Print(&p);

    Pointer_Free(&p);
    return 0;
}