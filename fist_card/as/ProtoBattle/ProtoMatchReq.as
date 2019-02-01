package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoMatchReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoMatchReq";
		public var package_root:*;
		public  var message:*;
		public function ProtoMatchReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoMatchReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoMatchReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}