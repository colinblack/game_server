package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class CreateAllianceReq
	{
		public static const PROTO:String = "ProtoAlliance.CreateAllianceReq";
		public var package_root:*;
		public  var message:*;
		public var flag:int;
		public var name:Byte;
		public var description:Byte;
		public var applyType:int;
		public var applyLevelLimit:int;
		public function CreateAllianceReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			flag = undefined;
			name = undefined;
			description = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.flag = this.flag;
			this.name.pos = 0;
			this.description.pos = 0;
			serializeObj.applyType = this.applyType;
			serializeObj.applyLevelLimit = this.applyLevelLimit;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CreateAllianceReq
		{
			flag = undefined;
			name = undefined;
			description = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
			this.flag = msgObj.flag;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.description = new Byte();
			this.description.writeArrayBuffer(msgObj.description);
			this.description.pos = 0;
			this.applyType = msgObj.applyType;
			this.applyLevelLimit = msgObj.applyLevelLimit;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CreateAllianceReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}