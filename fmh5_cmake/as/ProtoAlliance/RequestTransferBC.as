package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestTransferBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestTransferBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var memberUid:int;
		public var otherName:Byte;
		public function RequestTransferBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			memberUid = undefined;
			otherName = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.memberUid = this.memberUid;
			this.otherName.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestTransferBC
		{
			aid = undefined;
			uid = undefined;
			memberUid = undefined;
			otherName = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.memberUid = msgObj.memberUid;
			this.otherName = new Byte();
			this.otherName.writeArrayBuffer(msgObj.otherName);
			this.otherName.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestTransferBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}