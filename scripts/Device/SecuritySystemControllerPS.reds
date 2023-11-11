@addMethod(SecuritySystemControllerPS)
protected final func ReinitializeSecuritySystemAttitudeGroup() {
    let attitudeGroup = this.m_attitudeGroup;
    this.m_attitudeGroup = TDBID.None();
    this.SetSecuritySystemAttitudeGroup(attitudeGroup);
}

@addMethod(SecuritySystemControllerPS)
protected func QueueSystemEvent(evt: ref<Event>, opt self: Bool) {
    if self {
        this.QueueEntityEvent(PersistentID.ExtractEntityID(this.GetID()), evt);
    }

    if IsDefined(this.m_agentsRegistry) {
        for agent in this.m_agentsRegistry.GetAgents() {
            this.QueueEntityEvent(PersistentID.ExtractEntityID(this.GetPS(agent.link).GetID()), evt);
        }
    }
}

@addMethod(SecuritySystemControllerPS)
protected func QueueSystemPSEvent(evt: ref<Event>, opt self: Bool) {
    if self {
        this.QueuePSEvent(this, evt);
    }

    if IsDefined(this.m_agentsRegistry) {
        for agent in this.m_agentsRegistry.GetAgents() {
            this.QueuePSEvent(this.GetPS(agent.link), evt);
        }
    }
}

@addMethod(SecuritySystemControllerPS)
protected func OnResetSecuritySystemNetwork(evt: ref<ResetSecuritySystemNetwork>) -> EntityNotificationType {
    if !this.m_agentsRegistry.IsReady() {
        this.CompileSecurityAgentRegistry();
    }

    this.QueueSystemPSEvent(this.ActionQuestForceDisabled());
    this.QueueSystemPSEvent(this.ActionQuestResetDeviceToInitialState());

    this.ReinitializeSecuritySystemAttitudeGroup();

    this.QueueSystemPSEvent(this.ActionQuestRestoreQuickHacks());
    this.QueueSystemPSEvent(this.ActionQuestForceEnabled());

    this.OnQuestForceON(this.ActionQuestForceON());

    this.QueueSystemPSEvent(this.ActionQuestResetPerfomedActionsStorage(), true);

    return EntityNotificationType.SendThisEventToEntity;
}
