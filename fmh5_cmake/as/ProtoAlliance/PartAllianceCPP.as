package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class PartAllianceCPP
	{
		public static const PROTO:String = "ProtoAlliance.PartAllianceCPP";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public var name:Byte;
		public var flag:int;
		public var applyType:int;
		public var applyLevelLimit:int;
		public var memberCount:int;
		public var description:Byte;
		public var onlineNum:int;
		public function PartAllianceCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
			name = undefined;
			flag = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
			memberCount = undefined;
			description = undefined;
			onlineNum = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			this.name.pos = 0;
			serializeObj.flag = this.flag;
			serializeObj.applyType = this.applyType;
			serializeObj.applyLevelLimit = this.applyLevelLimit;
			serializeObj.memberCount = this.memberCount;
			if(this.description!= undefined)
			{
				serializeObj.description = this.description.getUint8Array(0, this.description.length);
				this.description.pos = 0;
			}
			if(this.onlineNum!= undefined)
			{
				serializeObj.onlineNum = this.onlineNum;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PartAllianceCPP
		{
			allianceId = undefined;
			name = undefined;
			flag = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
			memberCount = undefined;
			description = undefined;
			onlineNum = undefined;
			this.allianceId = msgObj.allianceId;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.flag = msgObj.flag;
			this.applyType = msgObj.applyType;
			this.applyLevelLimit = msgObj.applyLevelLimit;
			this.memberCount = msgObj.memberCount;
			if(msgObj.hasOwnProperty("description"))
			{
				this.description = new Byte();
				this.description.writeArrayBuffer(msgObj.description);
				this.description.pos = 0;
			}
			if(msgObj.hasOwnProperty("onlineNum"))
			{
				this.onlineNum = msgObj.onlineNum;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PartAllianceCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}