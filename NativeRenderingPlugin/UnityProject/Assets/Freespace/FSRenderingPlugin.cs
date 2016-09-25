using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;

enum Event
{
    RenderTri = 1,
    RenderFS,
    Init,
    Deinit,
};

public class FSRenderingPlugin : MonoBehaviour
{
    #region Plugin Interface
    [DllImport("FSRenderingPlugin")]
    private static extern void SetTimeFromUnity(float t);

    [DllImport("FSRenderingPlugin")]
    private static extern IntPtr GetRenderEventFunc();

    [DllImport("FSRenderingPlugin")]
    private static extern void Plugin_Init([MarshalAs(UnmanagedType.LPStr)] string path);

    [DllImport("FSRenderingPlugin")]
    private static extern void Plugin_Deinit();

    delegate void myCallbackDelegate(string msg);
    [DllImport("FSRenderingPlugin")]
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
       // GL.IssuePluginEvent(GetRenderEventFunc(), (int)Event.RenderTri);
        GL.IssuePluginEvent(GetRenderEventFunc(), (int)Event.RenderFS);
    }

    void PluginDebugLog(string msg)
    {
        Debug.Log(msg);
    }
}
