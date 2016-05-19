# Changes due to ICompont refactoring...
#s/SetChannelId(ChannelId id)/SetChannelId(ChannelId id)/g
s/int channelId/ChannelId channelId/g
s/GetProxy([ ]*ENTITY_PROXY_RENDER[ ]*)/GetComponent<IComponentRender>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_RENDER[ ]*)/GetOrCreateComponent<IComponentRender>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_USER[ ]*)/GetComponent<IComponentUser>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_USER[ ]*)/GetOrCreateComponent<IComponentUser>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_ROPE[ ]*)/GetComponent<IComponentRope>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_ROPE[ ]*)/GetOrCreateComponent<IComponentRope>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_AUDIO[ ]*)/GetComponent<IComponentAudio>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_AUDIO[ ]*)/GetOrCreateComponent<IComponentAudio>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_SOUND[ ]*)/GetComponent<IComponentSound>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_SOUND[ ]*)/GetOrCreateComponent<IComponentSound>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_FLOWGRAPH[ ]*)/GetComponent<IComponentFlowGraph>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_FLOWGRAPH[ ]*)/GetOrCreateComponent<IComponentFlowGraph>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_PHYSICS[ ]*)/GetComponent<IComponentPhysics>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_PHYSICS[ ]*)/GetOrCreateComponent<IComponentPhysics>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_SCRIPT[ ]*)/GetComponent<IComponentScript>().get()/g
s/CreateProxy([ ]*ENTITY_PROXY_SCRIPT[ ]*)/GetOrCreateComponent<IComponentScript>().get()/g
s/GetProxy([ ]*ENTITY_PROXY_AREA[ ]*)/GetComponent<IComponentArea>.get()/g
s/CreateProxy([ ]*ENTITY_PROXY_AREA[ ]*)/GetOrCreateComponent<IComponentArea>.get()/g
s/GetProxy([ ]*ENTITY_PROXY_TRIGGER[ ]*)/GetComponent<IComponentTrigger>.get()/g
s/CreateProxy([ ]*ENTITY_PROXY_TRIGGER[ ]*)/GetOrCreateComponent<IComponentTrigge>.get()/g
s/GetProxy([ ]*ENTITY_PROXY_BOIDS[ ]*)/GetComponent<IComponentBoids>.get()/g
s/CreateProxy([ ]*ENTITY_PROXY_BOIDS[ ]*)/GetOrCreateComponent<IComponentBoids>.get()/g
s/GetProxy([ ]*ENTITY_PROXY_BOID_OBJECT[ ]*)/GetComponent<IComponentBoidObject>.get()/g
s/CreateProxy([ ]*ENTITY_PROXY_BOID_OBJECT[ ]*)/GetOrCreateComponent<IComponentBoidObject>.get()/g
# Transform Proxy names into Component Names in types
s/IEntity\([A-Za-z]*\)Proxy/IComponent\1/g
# FIx up ChannelId types in Components
s/SetChannelId *([ ]*uint16 *id *)/SetChannelId (ChannelId id)/
s/InitClient *( *int *channelId *)/InitClient (ChannelId channelId)/
s/PostInitClient *( *int *channelId *)/PostInitClient (ChannelId channelId)/
# Renamed class to fix spelling
s/IPersistantDebug/IPersistentDebug/g
s/__fsel/fsel/g
s/__fres/fres/g
