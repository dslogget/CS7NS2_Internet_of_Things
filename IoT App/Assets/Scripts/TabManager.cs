using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TabManager : MonoBehaviour
{
    private List<GameObject> panels;

    void Start()
    {
        panels = new List<GameObject>(GameObject.FindGameObjectsWithTag("Panel"));
    }

    public void SwitchPanel(GameObject currPanel)
    {
        GameObject currContent = currPanel.transform.Find("Content").gameObject;
        if (currContent.activeSelf)
        {
            return;
        }

        for (int i = 0; i < panels.Capacity; i++)
        {
            GameObject content = panels[i].transform.Find("Content").gameObject;
            if (content.activeSelf)
            {
                content.SetActive(false);
                currContent.SetActive(true);
            }
        }
    }
}