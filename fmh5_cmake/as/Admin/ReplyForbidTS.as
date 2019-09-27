package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class ReplyForbidTS
	{
		public static const PROTO:String = "Admin.ReplyForbidTS";
		public var package_root:*;
		public  var message:*;
		public var forbidts:int;
		public var reason:Byte;
		public function ReplyForbidTS(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			forbidts = undefined;
			reason = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.forbidts = this.forbidts;
			this.reason.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyForbidTS
		{
			forbidts = undefined;
			reason = undefined;
			this.forbidts = msgObj.forbidts;
			this.reason = new Byte();
			this.reason.writeArrayBuffer(msgObj.reason);
			this.reason.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyForbidTS
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}