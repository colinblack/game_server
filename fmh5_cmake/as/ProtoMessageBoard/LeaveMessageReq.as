package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class LeaveMessageReq
	{
		public static const PROTO:String = "ProtoMessageBoard.LeaveMessageReq";
		public var package_root:*;
		public  var message:*;
		public var masteruid:int;
		public var typeId:int;
		public var words:Byte;
		public function LeaveMessageReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			masteruid = undefined;
			typeId = undefined;
			words = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.masteruid = this.masteruid;
			serializeObj.typeId = this.typeId;
			this.words.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):LeaveMessageReq
		{
			masteruid = undefined;
			typeId = undefined;
			words = undefined;
			this.masteruid = msgObj.masteruid;
			this.typeId = msgObj.typeId;
			this.words = new Byte();
			this.words.writeArrayBuffer(msgObj.words);
			this.words.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):LeaveMessageReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}