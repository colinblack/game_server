package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ManipulateMemberReq
	{
		public static const PROTO:String = "ProtoAlliance.ManipulateMemberReq";
		public var package_root:*;
		public  var message:*;
		public var memberUid:int;
		public var operate:int;
		public var type:int;
		public var destination:int;
		public function ManipulateMemberReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			memberUid = undefined;
			operate = undefined;
			type = undefined;
			destination = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.memberUid = this.memberUid;
			serializeObj.operate = this.operate;
			serializeObj.type = this.type;
			serializeObj.destination = this.destination;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ManipulateMemberReq
		{
			memberUid = undefined;
			operate = undefined;
			type = undefined;
			destination = undefined;
			this.memberUid = msgObj.memberUid;
			this.operate = msgObj.operate;
			this.type = msgObj.type;
			this.destination = msgObj.destination;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ManipulateMemberReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}