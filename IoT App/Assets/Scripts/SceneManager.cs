using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Need to usr this class to store the datetime of each actuator
struct Actuator
{
    float value;
    DateTime datetime;
}

public class SceneManager : MonoBehaviour
{
    public float light = 0.0f;
    public float door = 0.0f;
    public float window = 0.0f;

    void Start()
    {
        Screen.fullScreen = false;
    }
}