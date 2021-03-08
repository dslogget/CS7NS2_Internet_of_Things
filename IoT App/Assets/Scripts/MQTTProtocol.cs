/*
The MIT License (MIT)

Copyright (c) 2018 Giovanni Paolo Vigano'

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using M2MqttUnity;
using TMPro;
using Michsky.UI.ModernUIPack;

/// <summary>
/// Examples for the M2MQTT library (https://github.com/eclipse/paho.mqtt.m2mqtt),
/// </summary>
namespace M2MqttUnity.Examples
{
    /// <summary>
    /// Script for testing M2MQTT with a Unity UI
    /// </summary>
    public class MQTTProtocol : M2MqttUnityClient
    {
        [Header("Depenedencies")]
        public GameObject sceneManagerGO;
        public GameObject textGO;
        [Header("User Interface")]
        public bool autoTest = false;
        [Tooltip("Set this to true to perform a testing cycle automatically on startup")]
        public TMP_InputField consoleInputField;
        public Toggle encryptedToggle;
        public TMP_InputField addressInputField;
        public TMP_InputField portInputField;
        public Button connectButton;
        public Button disconnectButton;
        public Button testPublishButton;
        public Button clearButton;
        public Button doorButton;
        public GameObject doorSlider;
        public Button windowButton;
        public GameObject windowSlider;

        private List<string> eventMessages = new List<string>();
        private bool updateUI = false;
        private SceneManager sceneManager;

        public void TestPublish()
        {
            client.Publish("M2MQTT_Unity/test", System.Text.Encoding.UTF8.GetBytes("Test message"), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
            Debug.Log("Test message published");
            AddUiMessage("Test message published.");
        }

        private void PublishString(string name, string data)
        {
            DateTime timestamp = DateTime.Now;
            string text = "{\"" + name + "\":\"" + data + "\":\"" + timestamp.ToShortDateString() + " " + timestamp.ToLongTimeString() + "\",\"username\":\"jordanhu\"}";
            client.Publish("M2MQTT_Unity/test", System.Text.Encoding.UTF8.GetBytes(text), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
            Debug.Log("Message published");
            AddUiMessage("Message published.");
        }

        private void PublishFloat(string name, float value)
        {
            DateTime timestamp = DateTime.Now;
            string text = "{\"" + name + "\":" + value.ToString() + ",\"timestamp\":\"" + timestamp.ToShortDateString() + " " + timestamp.ToLongTimeString() + "\",\"username\":\"jordanhu\"}";
            client.Publish("M2MQTT_Unity/test", System.Text.Encoding.UTF8.GetBytes(text), MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE, false);
            Debug.Log("Message published");
            AddUiMessage("Message published.");
        }

        private void SetValue(string name, float value)
        {
            PublishFloat(name, value);
        }

        private void ToggleValue(string name, ref float value, RadialSlider slider)
        {
            if(value > 0.0f)
            {
                value = 0.0f;
            }
            else
            {
                value = 1.0f;
            }

            if(slider != null)
            {
                slider.SliderValue = slider.maxValue * value;
                slider.UpdateUI();
            }

            PublishFloat(name, value);
        }

        public void ToggleLight()
        {
            ToggleValue("light", ref sceneManager.light, null);
        }

        public void SetDoorValue(float value)
        {
            if (client == null)
            {
                return;
            }
            else if (!client.IsConnected)
            {
                return;
            }

            RadialSlider slider = doorSlider.GetComponent<RadialSlider>();
            sceneManager.door = value / slider.maxValue;

            SwitchManager manager = doorButton.gameObject.GetComponent<SwitchManager>();
            if (sceneManager.door == 0)
            {
                if (manager.isOn)
                {
                    manager.AnimateSwitch();
                }
            }
            else
            {
                if (!manager.isOn)
                {
                    manager.AnimateSwitch();
                }
            }

            SetValue("door", sceneManager.door);
        }

        public void ToggleDoor()
        {
            RadialSlider slider = doorSlider.GetComponent<RadialSlider>();
            ToggleValue("door", ref sceneManager.door, slider);
        }

        public void SetWindowValue(float value)
        {
            if (client == null)
            {
                return;
            }
            else if (!client.IsConnected)
            {
                return;
            }

            RadialSlider slider = windowSlider.GetComponent<RadialSlider>();
            sceneManager.window = value / slider.maxValue;

            SwitchManager manager = windowButton.gameObject.GetComponent<SwitchManager>();
            if (sceneManager.window == 0)
            {
                if (manager.isOn)
                {
                    manager.AnimateSwitch();
                }
            }
            else
            {
                if (!manager.isOn)
                {
                    manager.AnimateSwitch();
                }
            }
            SetValue("window", sceneManager.window);
        }


        public void ToggleWindow()
        {
            RadialSlider slider = windowSlider.GetComponent<RadialSlider>();
            ToggleValue("window", ref sceneManager.window, slider);
        }
        
        public void SetBrokerAddress(string brokerAddress)
        {
            if (addressInputField && !updateUI)
            {
                this.brokerAddress = brokerAddress;
                PlayerPrefs.SetString("host", brokerAddress);
            }
        }

        public void SetBrokerPort(string brokerPort)
        {
            if (portInputField && !updateUI)
            {
                int.TryParse(brokerPort, out this.brokerPort);
                PlayerPrefs.SetString("port", brokerPort);
            }
        }

        public void SetEncrypted(bool isEncrypted)
        {
            this.isEncrypted = isEncrypted;
            PlayerPrefs.SetInt("encrypted", isEncrypted ? 1 : 0);
        }

        public void SetUiMessage(string msg)
        {
            if (consoleInputField != null)
            {
                consoleInputField.text = msg;
                updateUI = true;
            }
        }

        public void AddUiMessage(string msg)
        {
            if (consoleInputField != null)
            {
                consoleInputField.text += msg + "\n";
                updateUI = true;
            }
        }

        protected override void OnConnecting()
        {
            base.OnConnecting();
            TextMeshProUGUI text = textGO.GetComponent<TextMeshProUGUI>();
            text.SetText("Connection: <color=white>Connecting</color>");
            SetUiMessage("Connecting to Broker on " + brokerAddress + ":" + brokerPort.ToString() + "...\n");
        }

        protected override void OnConnected()
        {
            base.OnConnected();
            TextMeshProUGUI text = textGO.GetComponent<TextMeshProUGUI>();
            text.SetText("Connection: <color=green>Active</color>");
            SetUiMessage("Connected to Broker on " + brokerAddress + "\n");

            if (autoTest)
            {
                TestPublish();
            }
        }

        protected override void SubscribeTopics()
        {
            client.Subscribe(new string[] { "M2MQTT_Unity/test" }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
        }

        protected override void UnsubscribeTopics()
        {
            client.Unsubscribe(new string[] { "M2MQTT_Unity/test" });
        }

        protected override void OnConnectionFailed(string errorMessage)
        {
            TextMeshProUGUI text = textGO.GetComponent<TextMeshProUGUI>();
            text.SetText("Connection: <color=red>Inactive</color>");
            AddUiMessage("CONNECTION FAILED! " + errorMessage);
        }

        protected override void OnDisconnected()
        {
            TextMeshProUGUI text = textGO.GetComponent<TextMeshProUGUI>();
            text.SetText("Connection: <color=red>Inactive</color>");
            AddUiMessage("Disconnected.");
        }

        protected override void OnConnectionLost()
        {
            TextMeshProUGUI text = textGO.GetComponent<TextMeshProUGUI>();
            text.SetText("Connection: <color=red>Inactive</color>");
            AddUiMessage("CONNECTION LOST!");
        }

        private void UpdateUI()
        {
            if (client == null)
            {
                //Home Tab
                if (doorButton != null)
                {
                    doorButton.interactable = false;
                }
                /*if(doorSlider != null)
                {
                    doorSlider.interactable = false;
                }*/
                if (windowButton != null)
                {
                    windowButton.interactable = false;
                }

                //Terminal Tab
                if (connectButton != null)
                {
                    connectButton.interactable = true;
                }
                if (disconnectButton != null)
                {      
                    disconnectButton.interactable = false;
                }
                if (testPublishButton != null)
                {
                    testPublishButton.interactable = false;
                }
            }
            else
            {
                //Home Tab
                if (doorButton != null)
                {
                    doorButton.interactable = client.IsConnected;
                }
                if (windowButton != null)
                {
                    windowButton.interactable = client.IsConnected;
                }

                //Terminal Tab
                if (testPublishButton != null)
                {
                    testPublishButton.interactable = client.IsConnected;
                }
                if (disconnectButton != null)
                {
                    disconnectButton.interactable = client.IsConnected;
                }
                if (connectButton != null)
                {
                    connectButton.interactable = !client.IsConnected;
                }
            }
            if (addressInputField != null && connectButton != null)
            {
                addressInputField.interactable = connectButton.interactable;
                addressInputField.text = brokerAddress;
            }
            if (portInputField != null && connectButton != null)
            {
                portInputField.interactable = connectButton.interactable;
                portInputField.text = brokerPort.ToString();
            }
            if (encryptedToggle != null && connectButton != null)
            {
                encryptedToggle.interactable = connectButton.interactable;
                encryptedToggle.isOn = isEncrypted;
            }
            if (clearButton != null && connectButton != null)
            {
                clearButton.interactable = connectButton.interactable;
            }
            updateUI = false;
        }

        private void LoadPreviousSession()
        {
            if (PlayerPrefs.HasKey("encrypted"))
            {
                bool encrypted = Convert.ToBoolean(PlayerPrefs.GetInt("encrypted"));
                encryptedToggle.onValueChanged.Invoke(encrypted);
            }

            if (PlayerPrefs.HasKey("host"))
            {
                string brokerAddress = PlayerPrefs.GetString("host");
                addressInputField.onValueChanged.Invoke(brokerAddress);
            }

            if (PlayerPrefs.HasKey("port"))
            {
                string brokerPort = PlayerPrefs.GetString("port");
                portInputField.onValueChanged.Invoke(brokerPort);
            }
        }

        //This function should be implemented as Override Connect
        //Call base.connect to call original function
        //Add additional code after
        //Timeout needs to be implemented
        private IEnumerator RequestData()
        {
            while(true)
            {
                if(client != null)
                {
                    if (client.IsConnected)
                    {
                        PublishString("data", "request");
                        break;
                    }
                }
                yield return new WaitForEndOfFrame();
            }
        }

        protected override void Start()
        {
            sceneManager = sceneManagerGO.GetComponent<SceneManager>();
            LoadPreviousSession();
            SetUiMessage("Ready.");
            updateUI = true;

            base.Start();
            StartCoroutine(RequestData());
        }

        protected override void DecodeMessage(string topic, byte[] message)
        {
            string msg = System.Text.Encoding.UTF8.GetString(message);
            Debug.Log("Received: " + msg);

            //Debugging - Check if Json sent was valid
            //JSONObject obj = new JSONObject(msg);
            //Debug.Log("Received: " + obj["light"]);

            StoreMessage(msg);
            if (topic == "M2MQTT_Unity/test")
            {
                if (autoTest)
                {
                    autoTest = false;
                    Disconnect();
                }
            }
        }

        private void StoreMessage(string eventMsg)
        {
            eventMessages.Add(eventMsg);
        }

        private void ProcessMessage(string msg)
        {
            AddUiMessage("Received: " + msg);
        }

        protected override void Update()
        {
            base.Update(); // call ProcessMqttEvents()

            if (eventMessages.Count > 0)
            {
                foreach (string msg in eventMessages)
                {
                    ProcessMessage(msg);
                }
                eventMessages.Clear();
            }
            if (updateUI)
            {
                UpdateUI();
            }
        }

        private void OnDestroy()
        {
            Disconnect();
        }

        private void OnValidate()
        {
            if (autoTest)
            {
                autoConnect = true;
            }
        }
    }
}