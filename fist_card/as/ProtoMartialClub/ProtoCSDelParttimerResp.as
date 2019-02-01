package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSDelParttimerResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSDelParttimerResp";
		public var package_root:*;
		public  var message:*;
		public function ProtoCSDelParttimerResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSDelParttimerResp
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSDelParttimerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}