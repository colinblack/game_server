package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoDelParttimerResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoDelParttimerResp";
		public var package_root:*;
		public  var message:*;
		public function ProtoDelParttimerResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoDelParttimerResp
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoDelParttimerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}