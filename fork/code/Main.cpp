#include <iostream>
#include <string_view>
#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>
//forward
typedef struct GLFWwindow GLFWwindow;
//typedef
using tTestKey = std::string_view;
using tTestFun = std::function<int(void)>;
using tTestTab = const std::unordered_map<tTestKey, tTestFun>;
using tTestRef = tTestTab::const_iterator;
//actions
int main(int vArgC, char **vArgV)
{
  if (vArgC == 3 ? (std::string_view(vArgV[1]) == "test") : 0)
  {
    extern tTestTab vTestTab;
    tTestRef vTestRef = vTestTab.find(vArgV[2]);
    if (vTestRef == vTestTab.end())
    {
      return EXIT_FAILURE;
    }
    else
    {
      std::cout << vTestRef->first << "=" << std::endl;
      auto vCode = vTestRef->second();
      std::cout << "=" << vTestRef->first << std::endl;
      return vCode;
    }
  }
  else
  {
    std::copy(
      &vArgV[0],
      &vArgV[vArgC],
      std::ostream_iterator<char*>(std::cout, "\n")
    );
  }
  return EXIT_SUCCESS;
}//main
using tKeyFun = std::function<void(GLFWwindow*vWindow, int vActn, int vMods)>;
using tKeyMap = std::unordered_map<int, tKeyFun>;
using tKeyRef = tKeyMap::iterator;
tKeyMap vKeyMap =
{
  {
    GLFW_KEY_Q,
    [](GLFWwindow* vWindow, int vActn, int vMods)
    {
      glfwSetWindowShouldClose(vWindow, 1);
    }
  },
};
void fKeyProc(GLFWwindow* vWindow, int vCode, int _, int vActn, int vMods)
{
  auto vKeyRef = vKeyMap;
  if (tKeyRef vKeyRef = vKeyMap.find(vCode); vKeyRef != vKeyMap.end())
  {
    vKeyRef->second(vWindow, vActn, vMods);
  }
}//fKeyProc
tTestTab vTestTab = {
  { "HelloWorld",
    []()
    {
      std::cout << "HelloWorld" << std::endl;
      return EXIT_SUCCESS;
    }
  },//HelloWorld
  { "GlfwWindow",
    []()
    {
      if (glfwInit() == 0)
      {
        std::cerr << "failed glfw init";
        return EXIT_FAILURE;
      }
      GLFWwindow*vWindow = glfwCreateWindow(0xff,0xff, "GlfwWindow", NULL,NULL);
      if (vWindow == NULL)
      {
        std::cerr << "failed window creation";
        return EXIT_FAILURE;
      }
      glfwShowWindow(vWindow);
      glfwSetKeyCallback(vWindow, fKeyProc);
      for(int vFlag = 1; vFlag; vFlag = !glfwWindowShouldClose(vWindow))
      {
        glfwSwapBuffers(vWindow);
        glfwPollEvents();
      }
      std::cout << "GlfwWindow_Success" << std::endl;
      return EXIT_SUCCESS;
    }
  },
};//vTestTab
