// on OpenGL ES there is no way to query texture extents from native texture id
#if (UNITY_IPHONE || UNITY_ANDROID) && !UNITY_EDITOR
	#define UNITY_GLES_RENDERER
#endif

using UnityEngine;
using System;
using System.Runtime.InteropServices;

enum Event
{
    Render = 1,
    Test,
    Init,
    Deinit,
};

public class UseRenderingPlugin : MonoBehaviour
{
    #region Plugin Interface
    [DllImport("RenderingPlugin")]
    private static extern void SetTimeFromUnity(float t);

    [DllImport("RenderingPlugin")]
    private static extern IntPtr GetRenderEventFunc();

    [DllImport("RenderingPlugin")]
    private static extern void Plugin_Init([MarshalAs(UnmanagedType.LPStr)] string path);

    [DllImport("RenderingPlugin")]
    private static extern void Plugin_Deinit();

    delegate void myCallbackDelegate(string msg);
    [DllImport("RenderingPlugin")]
    private static extern void Plugin_SetupDebug(myCallbackDelegate fp);
    #endregion

    Camera Cam;

    void Awake()
    {
        Plugin_SetupDebug(new myCallbackDelegate(PluginDebugLog));
    }

    void Start()
    {
        Cam = GetComponent<Camera>();

        Plugin_Init(Application.streamingAssetsPath);
        GL.IssuePluginEvent(GetRenderEventFunc(), (int) Event.Init);
    }

    void OnDestroy()
    {
        Plugin_Deinit();
        GL.IssuePluginEvent(GetRenderEventFunc(), (int) Event.Deinit);
    }

    void OnPostRender()
    {
        SetTimeFromUnity(Time.timeSinceLevelLoad);
        GL.IssuePluginEvent(GetRenderEventFunc(), (int)Event.Render);
    }

    void PluginDebugLog(string msg)
    {
        Debug.Log(msg);
    }
}
