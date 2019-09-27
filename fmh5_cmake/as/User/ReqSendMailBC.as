package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ReqSendMailBC
	{
		public static const PROTO:String = "User.ReqSendMailBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var ts:int;
		public var sys:Byte;
		public var reward:Byte;
		public function ReqSendMailBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			ts = undefined;
			sys = undefined;
			reward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.ts = this.ts;
			this.sys.pos = 0;
			this.reward.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReqSendMailBC
		{
			uid = undefined;
			ts = undefined;
			sys = undefined;
			reward = undefined;
			this.uid = msgObj.uid;
			this.ts = msgObj.ts;
			this.sys = new Byte();
			this.sys.writeArrayBuffer(msgObj.sys);
			this.sys.pos = 0;
			this.reward = new Byte();
			this.reward.writeArrayBuffer(msgObj.reward);
			this.reward.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReqSendMailBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}