package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetHeroResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetHeroResp";
		public var package_root:*;
		public  var message:*;
		public var hero:Vector.<MartialHeroInfo>;
		public function ProtoGetHeroResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			hero = new Vector.<MartialHeroInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.hero = [];
			for(var i:int = 0;i < this.hero.length;i++)
			{
				serializeObj.hero.push(this.hero[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetHeroResp
		{
			hero = new Vector.<MartialHeroInfo>();
			for(var i:int = 0;i < msgObj.hero.length;i++)
			{
				this.hero.push(new MartialHeroInfo(package_root).unserialize(msgObj.hero[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetHeroResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}