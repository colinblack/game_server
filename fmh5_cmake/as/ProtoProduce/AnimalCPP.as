package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class AnimalCPP
	{
		public static const PROTO:String = "ProtoProduce.AnimalCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var residenceUd:int;
		public var animalId:int;
		public var status:int;
		public var fullTime:int;
		public var keeper:int;
		public function AnimalCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			residenceUd = undefined;
			animalId = undefined;
			status = undefined;
			fullTime = undefined;
			keeper = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.residenceUd = this.residenceUd;
			serializeObj.animalId = this.animalId;
			serializeObj.status = this.status;
			serializeObj.fullTime = this.fullTime;
			if(this.keeper!= undefined)
			{
				serializeObj.keeper = this.keeper;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):AnimalCPP
		{
			ud = undefined;
			residenceUd = undefined;
			animalId = undefined;
			status = undefined;
			fullTime = undefined;
			keeper = undefined;
			this.ud = msgObj.ud;
			this.residenceUd = msgObj.residenceUd;
			this.animalId = msgObj.animalId;
			this.status = msgObj.status;
			this.fullTime = msgObj.fullTime;
			if(msgObj.hasOwnProperty("keeper"))
			{
				this.keeper = msgObj.keeper;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AnimalCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}