package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceCPP
	{
		public static const PROTO:String = "ProtoAlliance.AllianceCPP";
		public var package_root:*;
		public  var message:*;
		public var allianceId:int;
		public var name:Byte;
		public var flag:int;
		public var createUid:int;
		public var username:Byte;
		public var createTime:int;
		public var applyType:int;
		public var applyLevelLimit:int;
		public var description:Byte;
		public var qqgroup:int;
		public function AllianceCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = undefined;
			name = undefined;
			flag = undefined;
			createUid = undefined;
			username = undefined;
			createTime = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
			description = undefined;
			qqgroup = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = this.allianceId;
			this.name.pos = 0;
			serializeObj.flag = this.flag;
			serializeObj.createUid = this.createUid;
			this.username.pos = 0;
			serializeObj.createTime = this.createTime;
			serializeObj.applyType = this.applyType;
			serializeObj.applyLevelLimit = this.applyLevelLimit;
			if(this.description!= undefined)
			{
				serializeObj.description = this.description.getUint8Array(0, this.description.length);
				this.description.pos = 0;
			}
			serializeObj.qqgroup = this.qqgroup;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceCPP
		{
			allianceId = undefined;
			name = undefined;
			flag = undefined;
			createUid = undefined;
			username = undefined;
			createTime = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
			description = undefined;
			qqgroup = undefined;
			this.allianceId = msgObj.allianceId;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.flag = msgObj.flag;
			this.createUid = msgObj.createUid;
			this.username = new Byte();
			this.username.writeArrayBuffer(msgObj.username);
			this.username.pos = 0;
			this.createTime = msgObj.createTime;
			this.applyType = msgObj.applyType;
			this.applyLevelLimit = msgObj.applyLevelLimit;
			if(msgObj.hasOwnProperty("description"))
			{
				this.description = new Byte();
				this.description.writeArrayBuffer(msgObj.description);
				this.description.pos = 0;
			}
			this.qqgroup = msgObj.qqgroup;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}