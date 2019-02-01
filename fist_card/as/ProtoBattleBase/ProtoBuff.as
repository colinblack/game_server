package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBuff
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoBuff";
		public var package_root:*;
		public  var message:*;
		public function ProtoBuff(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBuff
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBuff
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}