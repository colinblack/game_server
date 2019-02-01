package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoRefreshReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoRefreshReq";
		public var package_root:*;
		public  var message:*;
		public function ProtoRefreshReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoRefreshReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoRefreshReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}