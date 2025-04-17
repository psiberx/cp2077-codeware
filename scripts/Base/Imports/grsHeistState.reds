public native struct grsHeistState {
  native let time: netTime;
  native let status: grsHeistStatus;
  native let playersInfo: [grsHeistPlayerGameInfo; 7];
}
