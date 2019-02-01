package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoMartialClubBattleResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoMartialClubBattleResp";
		public var package_root:*;
		public  var message:*;
		public var info:ProtoBattleDemo;
		public var commons:CommonItemsCPP;
		public function ProtoMartialClubBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.info = this.info.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoMartialClubBattleResp
		{
			info = undefined;
			commons = undefined;
			this.info = new ProtoBattleDemo(package_root).unserialize(msgObj.info);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoMartialClubBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}