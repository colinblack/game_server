package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class FruitCPP
	{
		public static const PROTO:String = "ProtoProduce.FruitCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var treeid:int;
		public var status:int;
		public var stage:int;
		public var fruitLeftNum:int;
		public var harvestTime:int;
		public var helpUid:int;
		public function FruitCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			treeid = undefined;
			status = undefined;
			stage = undefined;
			fruitLeftNum = undefined;
			harvestTime = undefined;
			helpUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.treeid = this.treeid;
			serializeObj.status = this.status;
			serializeObj.stage = this.stage;
			serializeObj.fruitLeftNum = this.fruitLeftNum;
			serializeObj.harvestTime = this.harvestTime;
			if(this.helpUid!= undefined)
			{
				serializeObj.helpUid = this.helpUid;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FruitCPP
		{
			ud = undefined;
			treeid = undefined;
			status = undefined;
			stage = undefined;
			fruitLeftNum = undefined;
			harvestTime = undefined;
			helpUid = undefined;
			this.ud = msgObj.ud;
			this.treeid = msgObj.treeid;
			this.status = msgObj.status;
			this.stage = msgObj.stage;
			this.fruitLeftNum = msgObj.fruitLeftNum;
			this.harvestTime = msgObj.harvestTime;
			if(msgObj.hasOwnProperty("helpUid"))
			{
				this.helpUid = msgObj.helpUid;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FruitCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}