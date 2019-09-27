package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class UnlockPetCPP
	{
		public static const PROTO:String = "ProtoPet.UnlockPetCPP";
		public var package_root:*;
		public  var message:*;
		public var petid:int;
		public var teaseEndts:int;
		public var normalEndts:int;
		public var teaseFlag:int;
		public var name:Byte;
		public function UnlockPetCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			petid = undefined;
			teaseEndts = undefined;
			normalEndts = undefined;
			teaseFlag = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.petid = this.petid;
			serializeObj.teaseEndts = this.teaseEndts;
			serializeObj.normalEndts = this.normalEndts;
			if(this.teaseFlag!= undefined)
			{
				serializeObj.teaseFlag = this.teaseFlag;
			}
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockPetCPP
		{
			petid = undefined;
			teaseEndts = undefined;
			normalEndts = undefined;
			teaseFlag = undefined;
			name = undefined;
			this.petid = msgObj.petid;
			this.teaseEndts = msgObj.teaseEndts;
			this.normalEndts = msgObj.normalEndts;
			if(msgObj.hasOwnProperty("teaseFlag"))
			{
				this.teaseFlag = msgObj.teaseFlag;
			}
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockPetCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}