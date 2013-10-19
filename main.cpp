#include <QApplication>
#include <mainwindow.h>
#include <includeshav.h>
#include <gl/glut.h>


static void HK_CALL errorReport(const char* msg, void* userContext)
{
    using namespace std;
    printf("%s", msg);
}

#define RETURN_FAIL_IF(COND, MSG) \
    HK_MULTILINE_MACRO_BEGIN \
        if(COND) { HK_ERROR(0x53a6a026, MSG); return 1; } \
    HK_MULTILINE_MACRO_END




int HK_CALL main( int argc,char* argv[])
{
    hkMallocAllocator baseMalloc;
    hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault( &baseMalloc, hkMemorySystem::FrameInfo(1024 * 1024) );
    hkBaseSystem::init( memoryRouter, errorReport );
    glutInit(&argc,argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#include <Common/Base/keycode.cxx>


#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#define HK_FEATURE_PRODUCT_PHYSICS
#define HK_FEATURE_REFLECTION_PHYSICS
#define HK_FEATURE_PRODUCT_ANIMATION
#define HK_FEATURE_REFLECTION_ANIMATION

#include <Common/Base/Config/hkProductFeatures.cxx>

namespace hkHavok660r1Classes
{
   extern const hkStaticClassNameRegistry hkHavokDefaultClassRegistry;
}

void HK_CALL CustomRegisterOverrideClasses(hkDynamicClassNameRegistry& registry)
{
   const hkStaticClassNameRegistry** regList = hkVersionRegistry::StaticLinkedClassRegistries;
   for ( const hkStaticClassNameRegistry** itr = regList; *itr != NULL; ++itr)
   {
      const hkStaticClassNameRegistry* oldRegistry = (*itr);
      if (const hkClass* hclass = oldRegistry->getClassByName("hkClassEnum") )
      {
         //if ( hclass->getSignature() == 0x9617a10c )
         if ( hclass->getSignature() == 0x9EE66732 )
         {
            registry.registerClass(hclass);
            return;
         }
      }
   }

   //const hkStaticClassNameRegistry& oldRegistry = hkHavok660r1Classes::hkHavokDefaultClassRegistry;

   //REGISTER_CLASS_W_SIG(, ##YYY)
}

