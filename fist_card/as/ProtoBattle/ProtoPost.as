package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoPost
	{
		public static const PROTO:String = "ProtoBattle.ProtoPost";
		public var package_root:*;
		public  var message:*;
		public var info:String;
		public function ProtoPost(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.info = this.info;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoPost
		{
			info = undefined;
			this.info = msgObj.info;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoPost
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}