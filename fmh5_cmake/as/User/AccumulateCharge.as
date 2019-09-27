package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class AccumulateCharge
	{
		public static const PROTO:String = "User.AccumulateCharge";
		public var package_root:*;
		public  var message:*;
		public var accumulateCharge:Vector.<ChargeItem>;
		public function AccumulateCharge(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			accumulateCharge = new Vector.<ChargeItem>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.accumulateCharge = [];
			for(var i:int = 0;i < this.accumulateCharge.length;i++)
			{
				serializeObj.accumulateCharge.push(this.accumulateCharge[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):AccumulateCharge
		{
			accumulateCharge = new Vector.<ChargeItem>();
			for(var i:int = 0;i < msgObj.accumulateCharge.length;i++)
			{
				this.accumulateCharge.push(new ChargeItem(package_root).unserialize(msgObj.accumulateCharge[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AccumulateCharge
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}