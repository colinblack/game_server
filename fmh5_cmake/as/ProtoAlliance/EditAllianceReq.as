package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class EditAllianceReq
	{
		public static const PROTO:String = "ProtoAlliance.EditAllianceReq";
		public var package_root:*;
		public  var message:*;
		public var flag:int;
		public var description:Byte;
		public var applyType:int;
		public var applyLevelLimit:int;
		public var qqgroup:int;
		public function EditAllianceReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			flag = undefined;
			description = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
			qqgroup = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.flag = this.flag;
			this.description.pos = 0;
			serializeObj.applyType = this.applyType;
			serializeObj.applyLevelLimit = this.applyLevelLimit;
			if(this.qqgroup!= undefined)
			{
				serializeObj.qqgroup = this.qqgroup;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):EditAllianceReq
		{
			flag = undefined;
			description = undefined;
			applyType = undefined;
			applyLevelLimit = undefined;
			qqgroup = undefined;
			this.flag = msgObj.flag;
			this.description = new Byte();
			this.description.writeArrayBuffer(msgObj.description);
			this.description.pos = 0;
			this.applyType = msgObj.applyType;
			this.applyLevelLimit = msgObj.applyLevelLimit;
			if(msgObj.hasOwnProperty("qqgroup"))
			{
				this.qqgroup = msgObj.qqgroup;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):EditAllianceReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}