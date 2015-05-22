#include "UniversalInputManager.h"


UniversalInputManager::UniversalInputManager() :
  m_listHead(NULL),
  m_callback(NULL)
{
}


size_t UniversalInputManager::poll()
{
  size_t updatedDevices = 0;
  UIMListNode * item = m_listHead;

  while(item != NULL)
  {
    IInputDevice * device = item->device;

    if(device->poll())
    {
      updatedDevices++;

      if(m_callback)
        m_callback(device->type(), device);
    }

    item = item->next;
  }

  return updatedDevices;
}


void UniversalInputManager::setCallback(inputcallback_t callback)
{
  m_callback = callback;
}


bool UniversalInputManager::addDevice(IInputDevice * device)
{
  UIMListNode * newNode = new UIMListNode();
  newNode->device = device;
  newNode->next = NULL;

  if(m_listHead == NULL)
  {
    m_listHead = newNode;
  }
  else
  {
    UIMListNode * item = m_listHead;
    while(item->next != NULL)
    {
      if(item->device->getID() == device->getID())
        return false;

      item = item->next;
    }

    if(item->device->getID() == device->getID())
      return false;

    item->next = newNode;
  }

  m_numDevices++;
  return true;
}
