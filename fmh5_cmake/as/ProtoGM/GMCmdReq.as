package com.sanguo.game.server.connectlogic.common.message.ProtoGM
{
	import laya.utils.Byte;
	public class GMCmdReq
	{
		public static const PROTO:String = "ProtoGM.GMCmdReq";
		public var package_root:*;
		public  var message:*;
		public var cmd:String;
		public function GMCmdReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cmd = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cmd = this.cmd;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GMCmdReq
		{
			cmd = undefined;
			this.cmd = msgObj.cmd;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GMCmdReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}