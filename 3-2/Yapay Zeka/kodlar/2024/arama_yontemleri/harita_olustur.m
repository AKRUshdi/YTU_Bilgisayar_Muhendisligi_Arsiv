function [sehir_koor,sq_sdist] = harita_olustur(sehir_sayisi,ekm,ekv,sil_oran)
%sehir sayisina g�re harita olu�turur, yollar�n uzunlu�u �klid
%yollar�n mevcut �klid uzunlu�una ekm ortalamal� ekv varyansli bir dagilimin pozitif tarafindan maliyet ekler  
%tum olas� yollar�n en uzunlar�ndan sil_oran kadarini siler

sehir_koor=rand(sehir_sayisi,2)*100;
sdist=pdist(sehir_koor);
ek=repmat(ekm,size(sdist,2),1) + abs(randn(size(sdist,2),1)*ekv);
sdist=round(sdist+ek');
sdist_uz=size(sdist,2);
% sildikten sonra hala her yerden her yere gidilebildi�inden emin olmak
% i�in minspantree olu�turup saklayalim
k=1;
S=zeros(1,sdist_uz);
T=S;
for s=1:sehir_sayisi
    for t=s+1:sehir_sayisi
        S(k)=s;
        T(k)=t;
        k=k+1;
    end
end
weights = sdist;
G = graph(S,T,weights);
[T,pred] = minspantree(G);
mst=T.Edges.EndNodes;
mst_size=size(mst,1);

% bazi yollari silelim
yed_sdist=sdist;
sq_yed_sdist = squareform(yed_sdist);
%sil_oran=0.8; %yollarin ne kadarini silelim
[di, ds]=sort(sdist,'descend'); %uzun yollari silelim
sil_indis=ds(1:round(sdist_uz*sil_oran));
sdist(sil_indis)=0;
sq_sdist = squareform(sdist);

%MST yi ekleyelim
for i=1:mst_size
    sq_sdist(mst(i,1),mst(i,2))=sq_yed_sdist(mst(i,1),mst(i,2));
    sq_sdist(mst(i,2),mst(i,1))=sq_yed_sdist(mst(i,2),mst(i,1));
end


end
