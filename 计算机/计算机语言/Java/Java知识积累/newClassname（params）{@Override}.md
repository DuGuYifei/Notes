# new classname（params）{@Override}

```Java
new FindServiceBehaviour(this, "alchemist") {
                    @Override
                    protected void onResult(DFAgentDescription[] services) {
                        if (services != null && services.length > 0) {
                            AID alchemist = services[0].getName();
                            SellPotion action = new SellPotion(new Potion("Heroic Potion"));
                            RequestPotionBehaviour request = new RequestPotionBehaviour(Mage.this, alchemist, action);
                            ((SequentialBehaviour) getParent()).addSubBehaviour(request);
                        }
                    }
                }
```

相当于创建了一个子类的实例