package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSSetHeroResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSSetHeroResp";
		public var package_root:*;
		public  var message:*;
		public var setHero:MartialHeroInfo;
		public function ProtoCSSetHeroResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			setHero = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.setHero = this.setHero.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSSetHeroResp
		{
			setHero = undefined;
			this.setHero = new MartialHeroInfo(package_root).unserialize(msgObj.setHero);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSSetHeroResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}