package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class SendNotifyReq
	{
		public static const PROTO:String = "ProtoAlliance.SendNotifyReq";
		public var package_root:*;
		public  var message:*;
		public var content:Byte;
		public function SendNotifyReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			content = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			this.content.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendNotifyReq
		{
			content = undefined;
			this.content = new Byte();
			this.content.writeArrayBuffer(msgObj.content);
			this.content.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SendNotifyReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}